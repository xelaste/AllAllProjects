package com.eci.chalenge.services;

import com.eci.chalenge.repository.TST;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.inject.Inject;
import javax.inject.Provider;

@Component
public class CompleteSuggestionService {
    @Inject
    private Provider<TST<Integer>> tstProvider;
    @Value("${user.home}/eci/OUT")
    private String dir;
}
