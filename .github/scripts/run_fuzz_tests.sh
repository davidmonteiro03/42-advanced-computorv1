#!/usr/bin/env bash
set -euo pipefail

# Script de fuzz / stress que executa muitos inputs (válidos/invalidos/limite) contra os binários
# Espera-se que o workflow anterior tenha criado: computor_mandatory e computor_bonus
BIN_MAND="./computor_mandatory"
BIN_BONUS="./computor_bonus"
TIMEOUT_CMD="timeout 5s"

# Fallback se não existirem os nomes movidos no workflow
if [ ! -x "$BIN_MAND" ]; then
  if [ -x "./computor" ]; then
    BIN_MAND="./computor"
  else
    echo "Aviso: binário mandatório não encontrado ('$BIN_MAND' ou './computor')"
  fi
fi
if [ ! -x "$BIN_BONUS" ]; then
  if [ -x "./computor" ]; then
    BIN_BONUS="./computor"
  else
    echo "Aviso: binário bônus não encontrado ('$BIN_BONUS' ou './computor')"
  fi
fi

run_and_check() {
  local bin="$1"
  local input="$2"
  # imprime cabeçalho simples
  printf "\n--- Running (%s) with input length=%d ---\n" "$bin" "${#input}"
  # usar timeout para evitar hangs
  echo "$input" | $TIMEOUT_CMD "$bin" || {
    local rc=$?
    echo "Process exited with code $rc (possible crash). Failing workflow."
    exit 1
  }
}

# Conjunto determinístico de casos para tentar quebrar parser/solver
declare -a CASES

# 1) Inputs vazios / espaços
CASES+=("")
CASES+=("    ")
CASES+=("=")

# 2) Inputs válidos simples
CASES+=("1 * X^0 = 1 * X^0")
CASES+=("5 * X^0 + 4 * X^1 = 2 * X^0")
CASES+=("0 * X^2 = 0 * X^2")

# 3) Inputs sintaticamente inválidos
CASES+=("** **")
CASES+=("1 ** X^1 = 0")
CASES+=("1 * X ^ ^ 2 = 0")
CASES+=("1 * X^ - 2 = 0")

# 4) Muitos operadores seguidos
CASES+=("+++++")
CASES+=("1 * X^1 + - + - * X ^ 2 = = =")

# 5) Tokens estranhos / UTF-8
CASES+=("糟糕 * X^2 = 1")
CASES+=("1 * X^2 = \xFF\xFE\xFA")

# 6) Valores incomuns (muito grandes, floats, negativos)
CASES+=("999999999999999999999999 * X^1 = 1")
CASES+=("1.23456789012345678901234567890 * X^2 = 0")
CASES+=("-1 * X^2 + -2 * X^1 = -3 * X^0")

# 7) Grau negativo (deve ser rejeitado)
CASES+=("1 * X^-1 = 0")
CASES+=("1 * X^--2 = 0")

# 8) Caso de memória: linha muito longa (1e6 bytes)
CASES+=("$(python3 - <<'PY'
print('1 * X^1 ' + ('+ 1 * X^1 ' * 20000))
PY
)")

# 9) Input com milhares de tokens (stress)
CASES+=("$(python3 - <<'PY'
print(' '.join(['1','*','X^1','='] + ['1','*','X^1','+']*5000))
PY
)")

# 10) Repetição de X sem operador
CASES+=("X X X X X X X X X X = 0")

# 11) Edge: zeros e signos misturados
CASES+=("+ - + - 0 * X^0 = - + 0 * X^0")

# Executa todos os casos contra ambos os binários (se existirem)
for c in "${CASES[@]}"; do
  # evitar input vazio direto em alguns bins se não existir
  if [ -x "$BIN_MAND" ]; then
    run_and_check "$BIN_MAND" "$c"
  fi
  if [ -x "$BIN_BONUS" ]; then
    run_and_check "$BIN_BONUS" "$c"
  fi
done

# Geração de fuzz simples: mutações de uma seed várias vezes
seed="1 * X^2 + 2 * X^1 = 3 * X^0"
for i in $(seq 1 200); do
  mutated=$(python3 - <<PY
import random
s = "${seed}"
ops = ['+', '-', '*', '^', '=', 'X', '1','2','3','99',' ']
s = ''.join(random.choice(ops) for _ in range(len(s)+random.randint(-5,20)))
print(s)
PY
)
  if [ -x "$BIN_MAND" ]; then
    run_and_check "$BIN_MAND" "$mutated"
  fi
  if [ -x "$BIN_BONUS" ]; then
    run_and_check "$BIN_BONUS" "$mutated"
  fi
done

echo "All tests completed without crash (sanitizers should report issues in stdout/stderr if any)."
