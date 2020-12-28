DROP TABLE IF EXISTS contact;
CREATE TABLE contact (
  id         INT         NOT NULL AUTO_INCREMENT,
  name       VARCHAR(20) NOT NULL,
  email VARCHAR(50) NOT NULL,
  phone VARCHAR(50) NOT NULL,
  campaign_id INT,		
  PRIMARY KEY (id)
 );
DROP TABLE IF EXISTS campaign CASCADE;
CREATE TABLE campaign (
  id         INT         NOT NULL AUTO_INCREMENT,
  name       VARCHAR(20) NOT NULL,
  mandatory_fields VARCHAR(50) NOT NULL,
  PRIMARY KEY (id)
 );
