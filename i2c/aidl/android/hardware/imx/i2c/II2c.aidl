package android.hardware.imx.i2c;

@VintfStability
interface II2c {
    boolean connect(in String port);
    boolean setSlave(in byte addr);
    boolean disconnect();
    byte sendByte(out byte[] data, in int len);
    byte readByte(out byte[] data, in int len);
}
