#include "ImuDaqDialog.h"
#include <QApplication>
#include "ImuEncode.pb.h"
#pragma warning(disable:4244)	// 禁止警告由double到float的降低精度问题

int main(int argc, char *argv[])
{
    std::cout << "initing ... ..." << std::endl;
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    QApplication a(argc, argv);
    QApplication::setStyle("fusion"); //"windows", "windowsvista", "fusion", or "macintosh"
    SetConsoleTitleA("IMU Program");
    ImuDaqDialog d;
    d.show();
    google::protobuf::ShutdownProtobufLibrary();
    return a.exec();
}
