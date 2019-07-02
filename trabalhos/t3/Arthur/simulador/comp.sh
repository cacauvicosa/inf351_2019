#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo "Uso: ./comp.sh nome_do_arquivo \[nome_de_saida\]"
	exit
fi

if [[ $# -eq 1 ]]; then
	g++ $1 -lGLU -lglut -lGL -lpthread
	exit
fi

g++ $1 -o $2 -lGLU -lglut -lGL -lpthread -Wall

