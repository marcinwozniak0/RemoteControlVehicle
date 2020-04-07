package user;

public class User {
    private String username;
    private final int vehicleId;
    private final int vehicleKey;
    
    User(String username, int vehicleId, int vehicleKey){
        this.username = username;
        this.vehicleId = vehicleId;
        this.vehicleKey = vehicleKey;
    }

    public String getUsername(){
        return this.username;
    }

    public int getVehicleId(){
        return this.vehicleId;
    }

    public int getVehicleKey(){
        return this.vehicleKey;
    }
}