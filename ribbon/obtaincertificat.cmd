setlocal
ssh -i ./id_muse_rsa -l epic muse-nbi-55.com rm -rf ~/xxx
ssh -i ./id_muse_rsa -l epic muse-nbi-55.com mkdir  ~/xxx
ssh -i ./id_muse_rsa -l epic muse-nbi-55.com "sudo cp /data/shared/PAAS/musei-ca-service/artifacts/muse-sbi/muse-sbi.crt ~epic/xxx/"
ssh -i ./id_muse_rsa -l epic muse-nbi-55.com "sudo cp /data/shared/PAAS/musei-ca-service/artifacts/muse-sbi/muse-sbi-privatekey.pem ~epic/xxx/"
ssh -i ./id_muse_rsa -l epic muse-nbi-55.com "echo $(sudo docker exec -i $(sudo docker ps -q --filter name=epic_musei-ca-service) cat /run/secrets/sbi-pass-phrase && echo) > ~/xxx/pwd.txt"
ssh -i ./id_muse_rsa -l epic muse-nbi-55.com "cd ~/xxx && openssl pkcs12 -export -in muse-sbi.crt -inkey muse-sbi-privatekey.pem -passin file:pwd.txt -out muse-nbi-55.com.p12 -passout pass:12345"
scp -i ./id_muse_rsa  epic@muse-nbi-55.com:~/xxx/muse-nbi-55.com.p12 ./musacert/muse-nbi-55.com/xxx/muse-nbi-55.com.p12
echo | openssl s_client -servername muse-nbi-55.com -connect muse-nbi-55.com:443 | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > certificate.crt
%JAVA_HOME%\bin\keytool -delete -trustcacerts -keystore %JAVA_HOME%\jre\lib\security\cacerts -storepass changeit -noprompt -alias muse-nbi-55.com
%JAVA_HOME%\bin\keytool -import -trustcacerts -keystore %JAVA_HOME%\jre\lib\security\cacerts -storepass changeit -noprompt -alias muse-nbi-55.com -file certificate.crt
endlocal