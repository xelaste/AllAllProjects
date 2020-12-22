package com.travelfactory.candidate.catalog.entities;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Room {
	@Id
	private String id;
    private String name;
    private Integer number;

    public Room() {}

    public Room(String id, String name, Integer number) {
        this.id = id;
        this.name = name;
        this.number = number;
    }


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }


    public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Integer getNumber() {
		return number;
	}

	public void setNumber(Integer number) {
		this.number = number;
	}

	@Override
    public String toString() {
        return "Room{" +
                "id=" + id +
                ", name=" + name +
                ", number='" + number + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if ( !(o instanceof Room)) return false;
        Room room = (Room) o;
        if (!id.equals(room.id)) return false;
        if (name != null ? !name.equals(room.name) : room.name != null) return false;
        if (number != null ? !number.equals(room.number) : room.number != null) return false;
        return true;
    }

    @Override
    public int hashCode() {
        int result = id.hashCode();
        result = 31 * result + id.hashCode();
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (number != null ? number.hashCode() : 0);
        return result;
    }
}
