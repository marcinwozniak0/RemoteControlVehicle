#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "GrpcCommandSender.hpp"
#include "CommandReceiver.hpp"
#include "Number.hpp"

int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    GrpcCommandReceiver commandReceiver("127.0.0.1:3000");
    GrpcCommandSender commandSender(std::make_shared<Router::Stub>(
        grpc::CreateChannel("127.0.0.1:5000",
                            grpc::InsecureChannelCredentials())));

    QQmlApplicationEngine engine;
    Number number;
    engine.rootContext()->setContextProperty("cppNumber", &number);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine,
                     &QQmlApplicationEngine::objectCreated,
                     &app,
                     [url](QObject *obj, const QUrl &objUrl)
                     {
                         if (!obj && url == objUrl)
                         {
                             QCoreApplication::exit(-1);
                         }
                     },
                    Qt::QueuedConnection);

    engine.load(url);

    const auto exitStatus = app.exec();

    google::protobuf::ShutdownProtobufLibrary();

    return exitStatus;
}
