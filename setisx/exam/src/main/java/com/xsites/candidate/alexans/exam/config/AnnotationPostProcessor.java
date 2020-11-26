package com.xsites.candidate.alexans.exam.config;



import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanFactoryPostProcessor;
import org.springframework.beans.factory.config.ConfigurableListableBeanFactory;
import org.springframework.stereotype.Component;
@Component
public class AnnotationPostProcessor implements BeanFactoryPostProcessor {
	private static final Logger logger = LoggerFactory.getLogger(AnnotationPostProcessor.class);
	@Override
	public void postProcessBeanFactory(ConfigurableListableBeanFactory bf) throws BeansException 
	{
		 String[] beans = bf.getBeanDefinitionNames();
		    for (String s : beans) {
		        Class<?> beanType = bf.getType(s);
				/*
				 * logger.info("==============================");
				 * logger.info(beanType.getName());
				 * logger.info("==============================");
				 */
//		        bf.registerSingleton(name, newWS);
		        
		        }
		    }


	}


