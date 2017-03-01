#ifndef REGISTRO_H_INCLUDED
#define REGISTRO_H_INCLUDED

#include <cstdlib>
#include <cstdio>
#include <windows.h>

HKEY chave;

void criaRegistro()
{
    if( (RegCreateKey(HKEY_CURRENT_USER, "Minha Chave", &chave)) == 0)
        MessageBox(0, "Sucesso ao criar o registro", "OK", 0x10);
    RegCloseKey(chave);
}

bool abreRegistro()
{
    if( (RegOpenKey(HKEY_CURRENT_USER, "Minha Chave", &chave)) == 0)
            return true;
    else
        return false;
}

void setRegistro(char* nome)
{
    if(abreRegistro())
        if( (RegSetValueEx(chave, "Nome", 0, REG_SZ, (LPBYTE)nome, strlen(nome))) == 0)
            MessageBox(0, "Sucesso ao inserir valor na chave", "OK", 0x10);
    RegCloseKey(chave);
}

char* getRegistro()
{
    char nome[100];
    DWORD tipo, tamanho_buffer = 100;
    if(abreRegistro())
        if( (RegQueryValueEx(chave, "Nome",0, &tipo, (LPBYTE)nome, &tamanho_buffer)) == 0)
            MessageBox(0, nome, "O valor é: ", 0x40);
    RegCloseKey(chave);
    return nome;
}

void DelRegistro()
{
    if( (RegDeleteKey(HKEY_CURRENT_USER, "Minha Chave")) == 0)
        MessageBox(0, "Sucesso ao excluir a \"Minha Chave\"", "OK", 0x10);
}

#endif // REGISTRO_H_INCLUDED
