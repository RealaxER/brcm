package android.hardware.rpi.led;

@VintfStability
interface ILed {
    boolean init(in  String chipname, in int line, in String id);
    boolean requestOuput(in String id);
    void setOuput(in String id, in String val);
}
