package android.hardware.imx.uart;

@VintfStability
interface IUart {
    boolean connect(in String port, in int baud);
    boolean disconnect();
    byte sendByte(out byte[] data, in int len);
    byte readByte(out byte[] data, in int len);
}
