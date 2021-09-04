struct unit{
	int room;
	int course;
	int teacher;
	int group;
	};
struct entry{
	int code;
	char name[NAME_LEN];
	};
struct student{
	int group_code;
	int code;
	char name[NAME_LEN];
	};
/*struct unit units[TIME_UNITS][DAY_UNITS][MAX_UNITS];
struct entry courses [MAX_COURSES];
struct entry teachers[MAX_TEACHERS];
struct entry groups  [MAX_GROUPS];*/
