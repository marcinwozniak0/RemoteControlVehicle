package com.example.springboot;
// import javax.persistence.Entity;
// import javax.persistence.GeneratedValue;
// import javax.persistence.GenerationType;
// import javax.persistence.Id;

//@Entity
public class User {
     
    //@Id
    //@GeneratedValue(strategy = GenerationType.AUTO)
    private String username;
    private final int vehicleId;
    private final int vehicleKey;
    
    User(String username, int vehicleId, int vehicleKey){
        this.username = username;
        this.vehicleId = vehicleId;
        this.vehicleKey = vehicleKey;
    }

    String getUsername(){
        return this.username;
    }

    int getVehicleId(){
        return this.vehicleId;
    }

    int getVehicleKey(){
        return this.vehicleKey;
    }
    // standard constructors / setters / getters / toString
}