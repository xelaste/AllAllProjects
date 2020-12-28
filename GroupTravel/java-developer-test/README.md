# The JAVA programatic test for Travelfactory #


### The test during  3 hours and the goal is to create webservices with Spring Boot (h2 ###
### the resultat must be Jar and source code pushed in this repository. ###



* **Technological context**

The technological context is focused on high performance, microservices Restfull and scalability via docker.
This context is implemented with Spring Boot 2.3 with embeded database h2

* **Functional Context**

The TravelFactory marketing team need to store emails provided by partners or during contests.
 for this, the team marketing proposeto the IT department a project for a Storage contact system per campaign.

for example travelFactory marketing organizes:

-the campaign contest nov 2020:The participants of this contest will fill imperatively name and email into online form. 

-the contact recovery campaign via Facebook:The partner transmits the contacts one by one, imperatively with name, first name and email. 


**To do this microservice the following tasks must be performed:**

1.  Creating the spring boot project using (https://start.spring.io/)
 (Use of embedded h2 database and with JPA is highly recommended)


-------------------------------------------------------------


2.  Creating a WS CRUD of campaign

Example for insertion of a campaign
Method: Post 
URL : / marketing / ws / partner / campaign / {id}

Object Example
{
campagnName: ”contests”,
MandatoryFields: ['name']

}


-------------------------------------------------------------



3.  A contact registration web service

URL: / marketing / ws / partner / campaign / {Campaign Id} / registration
Method post
Example
{name : ”duran”,
First name: “martin”
mail: “vive@la.fr”
telephone: ”0122886655432”
}


Business rule 1: validation of data formats according to regex and the campaign mandatory fields

if mail is a mandatory for the campaign id
mail Format = "^ [\ w - \.] + @ ( [\ w -] + \.) + [\ w -] {2,4} $ "

phone: ^ [+] * [(] {0,1} [0-9] {1,4} [)] {0,1} [- \ s \ ./ 0-9] * $

if the format is not suitable, answer http code 400 with message code “wrong format for field {field}”

Business rule 2: if the contact does not exist in the database 
answer code 200 “ok”
otherwise code 409 ko