setlocal
set timestamp=%DATE:/=-%_%TIME::=-%
set timestamp=%timestamp: =%
mysqldump --skip-extended-insert  --host=ilptlpvnplan34.ecitele.com --port=3307 --user=lpUser --password=lpUser --databases plancoredb> plancoredb_%timestamp%.sql
mysqldump --skip-extended-insert  --host=ilptlpvnplan24.ecitele.com --port=3307 --user=lpUser --password=lpUser --databases plancoredb> plancoredb_$(date "+%Y.%m.%d-%H.%M.%S").sql

docker cp 21f974f6068e:plancoredb_2022.06.21-08.56.56.sql ./
endlocal