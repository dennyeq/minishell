#!/bin/bash

echo "===> INICIANDO TESTES FUNCIONAIS DO MINISHELL (AJUSTADO)"
MINISHELL=./minishell

echo "--- TESTANDO BUILTINS ---"

$MINISHELL << EOF
echo Hello World
exit
EOF

$MINISHELL << EOF
export TESTVAR=123
export
exit
EOF


$MINISHELL << EOF
pwd
exit
EOF

$MINISHELL << EOF
cd /
pwd
cd -
pwd
exit
EOF

$MINISHELL << EOF
unset TESTVAR
export
exit
EOF

echo "--- TESTANDO REDIRECIONAMENTO ---"

echo "Hello from minishell" > test_infile.txt

$MINISHELL << EOF
cat < test_infile.txt > test_outfile.txt
exit
EOF

if grep -q "Hello from minishell" test_outfile.txt; then
    echo "[✅] redirecionamento de entrada/saída"
else
    echo "[❌] redirecionamento falhou"
fi

echo "--- TESTANDO PIPE ---"

$MINISHELL << EOF
echo Hello World | grep Hello > pipe_out.txt
exit
EOF

if grep -q "Hello World" pipe_out.txt; then
    echo "[✅] pipe com redirecionamento"
else
    echo "[❌] pipe falhou"
fi

# Limpeza
rm -f test_infile.txt test_outfile.txt pipe_out.txt
