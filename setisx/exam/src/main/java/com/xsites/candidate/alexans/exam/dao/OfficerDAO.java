package com.xsites.candidate.alexans.exam.dao;


import java.util.List;
import java.util.Optional;

import com.xsites.candidate.alexans.exam.entities.Officer;

public interface OfficerDAO {
    Officer save(Officer officer);
    Optional<Officer> findById(Integer id);
    List<Officer> findAll();
    long count();
    void delete(Officer officer);
    boolean existsById(Integer id);
}
