#ifdef IIC_CREATE_PATTREN


class IIC
{
public:
    void start();                                                     //开始条件
    void stop();                                                      //停止条件
    void ACK_send();                                                  //发送应答
    void ACK_recive();                                                //接收应答
    void adv_id(bool rw, unsigned char t);                            //设备识别
    void write_k(unsigned char add, unsigned char data);              //字写入
    void write_p(unsigned char add, unsigned char *data_p);  //页写入
    void read_k(unsigned char add, unsigned char data);               //随机读取并检验
    void read_p(unsigned char add, int num, unsigned char *data_all); //顺序读取并检验
    void HALT();

private:
    char SCL, SDA;
}
//难过极了 
#endif
