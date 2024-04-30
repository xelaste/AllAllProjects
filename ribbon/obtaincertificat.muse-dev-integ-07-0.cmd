setlocal
ssh -i ./id_muse_rsa -l epic muse-dev-integ-07-0.com rm -rf ~/xxx
ssh -i ./id_muse_rsa -l epic muse-dev-integ-07-0.com mkdir  ~/xxx
ssh -i ./id_muse_rsa -l epic muse-dev-integ-07-0.com "sudo cp /data/shared/PAAS/musei-ca-service/artifacts/muse-sbi/muse-sbi.crt ~epic/xxx/"
ssh -i ./id_muse_rsa -l epic muse-dev-integ-07-0.com "sudo cp /data/shared/PAAS/musei-ca-service/artifacts/muse-sbi/muse-sbi-privatekey.pem ~epic/xxx/"
ssh -i ./id_muse_rsa -l epic muse-dev-integ-07-0.com "echo $(sudo docker exec -i $(sudo docker ps -q --filter name=epic_musei-ca-service) cat /run/secrets/sbi-pass-phrase && echo) > ~/xxx/pwd.txt"
ssh -i ./id_muse_rsa -l epic muse-dev-integ-07-0.com "cd ~/xxx && openssl pkcs12 -export -in muse-sbi.crt -inkey muse-sbi-privatekey.pem -passin file:pwd.txt -out muse-dev-integ-07-0.com.p12 -passout pass:12345"
rm -r ./musacert/muse-dev-integ-07-0.com/xxx
mkdir "./musacert/muse-dev-integ-07-0.com/xxx"
scp -i ./id_muse_rsa  epic@muse-dev-integ-07-0.com:~/xxx/muse-dev-integ-07-0.com.p12 ./musacert/muse-dev-integ-07-0.com/xxx/muse-dev-integ-07-0.com.p12
echo | openssl s_client -servername muse-dev-integ-07-0.com -connect muse-dev-integ-07-0.com:443 | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > certificate.crt
%JAVA_HOME%\bin\keytool -delete -trustcacerts -keystore %JAVA_HOME%\jre\lib\security\cacerts -storepass changeit -noprompt -alias muse-dev-integ-07-0.com
%JAVA_HOME%\bin\keytool -import -trustcacerts -keystore %JAVA_HOME%\jre\lib\security\cacerts -storepass changeit -noprompt -alias muse-dev-integ-07-0.com -file certificate.crt
endlocal