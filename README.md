# ImuDAQ-ImuDataProcesser
> Based on Qt 5.12.2 MSVC2017 32bit
This program is used for imu data aquisition and imu data processing.(changingseries is a old version in which all information for Reference Only)
## library
1. Lpsensor library is used to get imu data from Lp sensors.
2. Protocol Buffer is used for encoding imudata to a kind of structed data, and these datasets will be transmitted by Tcp/IP.

## The difference with ImuDAQ
1. ImuDAQ-ImuDataProcesser has all function in ImuDAQ(ImuSend),and it used GUI to replace cmd to achieve human-computer interaction.
2. ImuDAQ-ImuDataProcesser adds QCamera model to get image corresponding to every signal.
3. ImuDAQ-ImuDataProcesser adds ImuDataProcesser to this application to visualize data.
    the main qt models as follow in *.pro file.
    ```qmake
    QT       += charts
    QT       += multimedia multimediawidgets
    ```
