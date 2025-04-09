#!/bin/bash

# Compila e executa o minishell com comandos de teste
echo "export VAR1=hello" > test_input.txt
echo "export VAR2='foo bar'" >> test_input.txt
echo "export VAR3=123" >> test_input.txt
echo "export VAR4" >> test_input.txt
echo "export 1INVALID=value" >> test_input.txt
echo "export VAR+ERR=oops" >> test_input.txt
echo "export VAR1='updated again'" >> test_input.txt
echo "export" >> test_input.txt
echo "exit" >> test_input.txt

# Roda o minishell alimentando os comandos
echo "===> RODANDO TESTE DO EXPORT..."
cat test_input.txt | ./minishell
