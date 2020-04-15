package user;

public class User {
    private final int userId;
    private final int vehicleId;
    private final String vehicleKey;
    
    User(int userId, int vehicleId, String vehicleKey){
        this.userId = userId;
        this.vehicleId = vehicleId;
        this.vehicleKey = vehicleKey;
    }

    public int getUserId(){
        return this.userId;
    }

    public int getVehicleId(){
        return this.vehicleId;
    }

    public String getVehicleKey(){
        return this.vehicleKey;
    }
}