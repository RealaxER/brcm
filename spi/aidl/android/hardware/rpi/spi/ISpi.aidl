package android.hardware.rpi.spi;

@VintfStability
interface ISpi{
    boolean connect(in String port, in int baud);
    boolean close();
    byte sendByte(out byte[] data, in int len);
    byte readByte(out byte[] data, in int len);
    byte transferByte(in byte[] tx, out byte[] rx, in int len);
}
