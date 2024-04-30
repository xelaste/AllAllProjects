package com.sdn.tosca.network.element.capability.lib;

import java.lang.annotation.Documented;
import java.lang.annotation.Retention;
import java.lang.annotation.Target;

import org.springframework.context.annotation.Import;

/**
 * Indicates that all SBI controllers enabled.
 *
 * This should be applied to a Spring java config and should have an accompanying '@Configuration' annotation.
 *
 * Loads all required beans
 */
@Retention(value = java.lang.annotation.RetentionPolicy.RUNTIME)
@Target(value = { java.lang.annotation.ElementType.TYPE })
@Documented
@Import({ToscaNetworkElementCapabilityConfiguration.class})
public @interface EnableToscaNetworkElementCapabilityInterface {

}
