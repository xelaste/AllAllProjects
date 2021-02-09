package com.eci.chalenge.rsclient;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class BERsClient
{
    @Value("${be.url}")
    private String providerURL;

}
/*
public class InventoryClient {

    @Inject
    @ConfigProperty(name = "INVENTORY_BASE_URI", defaultValue = "http://localhost:9085")
    private String baseUri;


    public List<String> getSystems() {
        return ClientBuilder.newClient()
                            .target(baseUri)
                            .path("/inventory/systems")
                            .request()
                            .header(HttpHeaders.CONTENT_TYPE, MediaType.APPLICATION_JSON)
                            .get(new GenericType<List<String>>(){});
    }

    // tag::getSystem[]
    public Observable<Properties> getSystem(String hostname) {
        return ClientBuilder.newClient()
                            .target(baseUri)
                            // tag::register[]
                            .register(RxObservableInvokerProvider.class)
                            // end::register[]
                            .path("/inventory/systems")
                            .path(hostname)
                            .request()
                            .header(HttpHeaders.CONTENT_TYPE, MediaType.APPLICATION_JSON)
                            // tag::rx[]
                            .rx(RxObservableInvoker.class)
                            // end::rx[]
                            .get(new GenericType<Properties>(){});
    }
    // end::getSystem[]
}

 */
