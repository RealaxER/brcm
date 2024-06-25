package android.hardware.imx.spi;

@VintfStability
interface ISpi{
    boolean connect(in String port, in int speed, in int bits, in int mode);
    boolean disconnect();
    byte sendByte(out byte[] data, in int len);
    byte readByte(out byte[] data, in int len);
    byte transferByte(in byte[] tx, out byte[] rx, in int len);
}
