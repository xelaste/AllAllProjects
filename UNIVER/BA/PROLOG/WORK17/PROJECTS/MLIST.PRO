/*
     MAILING LIST DATABASE EXAMPLE 
     -----------------------------

     The Mailing List consists of a database of records
     of the form:

     record( Title,Initials,Surname,Age,
             Company,
             Street,
             Town,
             County,
             Interest )

*/

format( [ title,initials,surname,age,company,road,town,county,interest] ).

verb(having).
verb(with).

constructor( -,'Age: ').
constructor( +,@nl & 'Address: ').
constructor(works_for,'is employed by: ').
constructor(lives_at,'Has a house at: ').
constructor(\,@nl).

record(
'Mr','I.J.','Harrison', 45,
'SPL International',
'The Charter',
'Abingdon',
'Oxon',
'Logic Programming').

record(
'Mr','H.L.K','Smithway', 34,
'National Carriers',
'45 Alexander Road',
'Reading',
'Berks',
'Expert Systems' ).

record(
'Mrs','U.J','Roberts',27,
'B.B.C. Radio',
'Broadcasting House',
'London',
'Middlesex',
'AI').

record(
'Dr','T.F.','Peterson', 59,
'I.C.I.',
'39-85 Westway Estate',
'Accrington',
'Lancs.',
'Medical Diagnosis').

record(
'Prof','T.E.','Wilkinson', 60,
'University of Edinburgh',
'Hope Park Square',
'Edinburgh',
'Scotland',
'Expert Systems' ).

record(
'Dr','T.K.','Quisling', 99,
'St. Batholemew Hostpital',
'Catherine Street',
'York',
'West Yorkshire',
'Medical Diagnosis').

record(
'Mr','M.U','Rawlinson', 25,
'Newcastle Logic Systems',
'Gravs Street',
'Newcastle',
'Tyneside',
'AI' ).

record(
'Sir','James','Crighton-Smith',38,
'No-one',
'The Manor House',
'Little Taddingdean',
'Rutland',
'Prolog programming techniques' ).


     
