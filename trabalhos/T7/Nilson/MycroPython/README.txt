Instalação do MicroPython

1 - Instalar o MicroPython
    sudo apt-get install python-pip

2 - Instalar o programa para gravar no embarcado
    sudo pip install esptool

3 - Apagar os dados que possam estar gravados no embarcado
    esptool.py --port /dev/ttyUSB0 erase_flash

4 - Download do Firmware do MicroPython de acordo com o embarcado
    http://micropython.org/download

5 - esptool.py –port /dev/ttyUSB0 –baud 460800 write_flash –flash_size=detect -fm dio 0 < Nome do Firmware(arquivo baixado) >

6 - Instalação do Picocom para fazer a comunicação com o embarcado via usb
    sudo apt-get install picocom

7 - Para acessar o embarcado
    picocom -b 115200 /dev/ttyUSB0

8 - Para configurar pelo WEBREPL
    import webrepl_setup
      comandos:
              E
              digite uma senha ser o para acesso ao embarcado
              clique para reiniciar

9 - Download para poder controla-lo apenas pelo Wi-Fi ultilize o arquivo webrepl.html
    https://github.com/micropython/webrepl

10 - Para fazer a conexão via Wi-Fi a senha é micropythoN

11 - Após, basta fazer import das bibliotecas para utiliza-las


Font:
https://youtu.be/jD1ZouJQtXo
