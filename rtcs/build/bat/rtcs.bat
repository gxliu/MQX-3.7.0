#!/bin/sh

source `dirname $0`/verify_dir.bat $1

rm -f *.h

cp -f ../../../rtcs/source/include/select.h .
cp -f ../../../rtcs/source/include/ftp.h .
cp -f ../../../rtcs/source/include/ftpc.h .
cp -f ../../../rtcs/source/include/ftpd.h .
cp -f ../../../rtcs/source/include/ftpd_msg.h .
cp -f ../../../rtcs/source/include/rtcsvers.h .
cp -f ../../../rtcs/source/include/rtcs.h .
cp -f ../../../rtcs/source/include/rtcsrtos.h .
cp -f ../../../rtcs/source/include/rtcstime.h .
cp -f ../../../rtcs/source/include/rtcscfg.h .
cp -f ../../../rtcs/source/include/rtcs_in.h .
cp -f ../../../rtcs/source/include/rtcshdlc.h .
cp -f ../../../rtcs/source/include/pppfsm.h .
cp -f ../../../rtcs/source/include/ppphdlc.h .
cp -f ../../../rtcs/source/include/ppp.h .
cp -f ../../../rtcs/source/include/dns.h .
cp -f ../../../rtcs/source/include/svc.h .
cp -f ../../../rtcs/source/include/svcauth.h .
cp -f ../../../rtcs/source/include/xdr.h .
cp -f ../../../rtcs/source/include/dhcp.h .
cp -f ../../../rtcs/source/include/rpctypes.h .
cp -f ../../../rtcs/source/include/rtcsrpc.h .
cp -f ../../../rtcs/source/include/rpcmsg.h .
cp -f ../../../rtcs/source/include/clnt.h .
cp -f ../../../rtcs/source/include/pmap.h .
cp -f ../../../rtcs/source/include/pmapif.h .
cp -f ../../../rtcs/source/include/auth.h .
# cp -f ../../../rtcs/source/include/iodun.h .
cp -f ../../../rtcs/source/include/rtcs25x.h .
cp -f ../../../rtcs/source/include/rtcslog.h .
cp -f ../../../rtcs/source/include/nat.h .
cp -f ../../../rtcs/source/include/nat_session.h .
cp -f ../../../rtcs/source/include/ipcfg.h .
cp -f ../../../rtcs/source/include/iwcfg.h .

cp -f ../../../rtcs/source/httpd/httpd.h .
cp -f ../../../rtcs/source/httpd/httpd_types.h .
cp -f ../../../rtcs/source/httpd/httpd_wrapper.h .
cp -f ../../../rtcs/source/httpd/httpd_mqx.h .
cp -f ../../../rtcs/source/httpd/httpd_supp.h .
cp -f ../../../rtcs/source/httpd/httpd_cnfg.h .


cp -f ../../../rtcs/source/include/snmp.h .
cp -f ../../../rtcs/source/include/snmpcfg.h .
cp -f ../../../rtcs/source/include/asn1.h .
cp -f ../../../rtcs/source/include/rtcspcb.h .

cp -f ../../../rtcs/source/include/tcp.h .
cp -f ../../../rtcs/source/include/ip.h .

cp -f ../../../rtcs/source/include/ipc_udp.h .


exit

@echo off

rem Make sure we are in target directory
call "%~dp0/verify_dir.bat" %1
if %ERRORLEVEL% NEQ 0 exit 1

if exist *.h  del /F /Q *.h

copy /Y ..\..\..\rtcs\source\include\select.h .
copy /Y ..\..\..\rtcs\source\include\ftp.h .
copy /Y ..\..\..\rtcs\source\include\ftpc.h .
copy /Y ..\..\..\rtcs\source\include\ftpd.h .
copy /Y ..\..\..\rtcs\source\include\ftpd_msg.h .
copy /Y ..\..\..\rtcs\source\include\rtcsvers.h .
copy /Y ..\..\..\rtcs\source\include\rtcs.h .
copy /Y ..\..\..\rtcs\source\include\rtcsrtos.h .
copy /Y ..\..\..\rtcs\source\include\rtcstime.h .
copy /Y ..\..\..\rtcs\source\include\rtcscfg.h .
copy /Y ..\..\..\rtcs\source\include\rtcs_in.h .
copy /Y ..\..\..\rtcs\source\include\rtcshdlc.h .
copy /Y ..\..\..\rtcs\source\include\pppfsm.h .
copy /Y ..\..\..\rtcs\source\include\ppphdlc.h .
copy /Y ..\..\..\rtcs\source\include\ppp.h .
copy /Y ..\..\..\rtcs\source\include\dns.h .
copy /Y ..\..\..\rtcs\source\include\svc.h .
copy /Y ..\..\..\rtcs\source\include\svcauth.h .
copy /Y ..\..\..\rtcs\source\include\xdr.h .
copy /Y ..\..\..\rtcs\source\include\dhcp.h .
copy /Y ..\..\..\rtcs\source\include\rpctypes.h .
copy /Y ..\..\..\rtcs\source\include\rtcsrpc.h .
copy /Y ..\..\..\rtcs\source\include\rpcmsg.h .
copy /Y ..\..\..\rtcs\source\include\clnt.h .
copy /Y ..\..\..\rtcs\source\include\pmap.h .
copy /Y ..\..\..\rtcs\source\include\pmapif.h .
copy /Y ..\..\..\rtcs\source\include\auth.h .
rem copy /Y ..\..\..\rtcs\source\include\iodun.h .
copy /Y ..\..\..\rtcs\source\include\rtcs25x.h .
copy /Y ..\..\..\rtcs\source\include\rtcslog.h .
copy /Y ..\..\..\rtcs\source\include\nat.h .
copy /Y ..\..\..\rtcs\source\include\nat_session.h .
copy /Y ..\..\..\rtcs\source\include\ipcfg.h .
copy /Y ..\..\..\rtcs\source\include\iwcfg.h .

copy /Y ..\..\..\rtcs\source\httpd\httpd.h .
copy /Y ..\..\..\rtcs\source\httpd\httpd_types.h .
copy /Y ..\..\..\rtcs\source\httpd\httpd_wrapper.h .
copy /Y ..\..\..\rtcs\source\httpd\httpd_mqx.h .
copy /Y ..\..\..\rtcs\source\httpd\httpd_supp.h .
copy /Y ..\..\..\rtcs\source\httpd\httpd_cnfg.h .


copy /Y ..\..\..\rtcs\source\include\snmp.h .
copy /Y ..\..\..\rtcs\source\include\snmpcfg.h .
copy /Y ..\..\..\rtcs\source\include\asn1.h .
copy /Y ..\..\..\rtcs\source\include\rtcspcb.h .

copy /Y ..\..\..\rtcs\source\include\tcp.h .
copy /Y ..\..\..\rtcs\source\include\ip.h .

copy /Y ..\..\..\rtcs\source\include\ipc_udp.h .
