// ## VERSION: V.0.0 | Initial Version ##
// ## COMMIT: Fixed LoRa CLASS change, BUG CLASS-C ##
// ## ORG: Sensornode IoT Technology Sole Co., Ltd ##
// ## DEV: Mr. Tee Chuangthevy @ 2023 ##
// ## DATE: 28 APRIL 2023 ##

class SensorLink
{
public:
    String rcv;
    String reboot;

    SensorLink();
    String payload(String at);
    String atcmd_key(String at);
    String atcmd_status(String at, String _t1_, String _t2_);
    String atcmd_text(String at);
    String atcmd_int(String at);
    String atcmd_hex(String at);
    String check_payload(String at);
    bool atcmd_set(String at, String nvalue);
    void set_reboot();
    void wait(int wtime);
    bool join();
    bool join_adp();
    String get_module();
    String get_appeui();
    String get_appkey();
    String get_appskey();
    String get_nwkskey();
    String get_devaddr();
    String get_deveui();
    String get_cfm();
    String get_recv();
    bool send(int p, String t);
    bool lpsend(int p, int a, String t);
    String get_cfs();
    String get_njm();
    String get_njs();
    String get_adr();
    String get_loraclass();
    String get_dcs();
    String get_dr();
    String get_jn1dl();
    String get_jn2dl();
    String get_pnm();
    String get_rx1dl();
    String get_rx2dl();
    String get_rx2dr();
    String get_rx2fq();
    String get_txp();
    String get_rssi();
    String get_lbtrssi();
    String get_snr();
    String get_ver();

    String dport;
    String dpayload;

    bool set_appeui(String _NVALUE_);
    bool set_appkey(String _NVALUE_);
    bool set_appskey(String _NVALUE_);
    bool set_devaddr(String _NVALUE_);
    bool set_deveui(String _NVALUE_);
    bool set_nwkskey(String _NVALUE_);
    bool set_cfm(String _NVALUE_);
    bool set_cfs(String _NVALUE_);
    bool set_adr(String _NVALUE_);
    bool set_dcs(String _NVALUE_);
    bool set_dr(String _NVALUE_);
    bool set_jn1dl(String _NVALUE_);
    bool set_jn2dl(String _NVALUE_);
    bool set_pnm(String _NVALUE_);
    bool set_rx1dl(String _NVALUE_);
    bool set_rx2dl(String _NVALUE_);
    bool set_rx2dr(String _NVALUE_);
    bool set_rx2fq(String _NVALUE_);
    bool set_txp(String _NVALUE_);
    bool set_loraclass(String _NVALUE_);

private:
    String return_text;
    bool return_bool;
};