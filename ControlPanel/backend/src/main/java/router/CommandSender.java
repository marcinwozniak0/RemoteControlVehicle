package router;

import com.interfaces.proto.InitCommandsProto.*;
import com.interfaces.proto.AcknowledgeProto.Acknowledge;
import com.interfaces.proto.AcknowledgeStatus.Status;
import com.interfaces.proto.RouterGrpc;
import com.google.protobuf.Any;
import io.grpc.ManagedChannel;
import io.grpc.ManagedChannelBuilder;

public class CommandSender {
    private RouterGrpc.RouterBlockingStub stub;
    private ManagedChannel channel;

    public CommandSender() {
    channel = ManagedChannelBuilder.forAddress("localhost", 5000)
    .usePlaintext()
    .build();

    stub = RouterGrpc.newBlockingStub(channel);

    HelloReply helloReply = stub.sayHello(HelloRequest.newBuilder()
        .setName("JAVA command sender")
        .build());
    }

    public boolean sendCommand(Any commandToSend){

        Acknowledge acknowledge = stub.sendCommand(commandToSend);

        if (Status.SUCCESS == acknowledge.getStatus()){
            return true;
        }
        else{
            return false;
        }
    }
}