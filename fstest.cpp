#include<iostream>

struct _pid
{
     float SetSpeed;            //定义设定值
     float ActualSpeed;        //定义实际值
     float err;                //定义偏差值
     float err_last;            //定义上一个偏差值
     float Kp,Ki,Kd;            //定义比例、积分、微分系数
     float voltage;            //定义电压值（控制执行器的变量）
     float integral;            //定义积分值
}pid;
void PID_init()
{
    printf("PID_init begin \n");
    pid.SetSpeed=0.0;
    pid.ActualSpeed=0.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.5;
    pid.Ki=0.02;
    pid.Kd=0.2;
    printf("PID_init end \n");
}
float PID_realize(float speed)
{
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    pid.integral+=pid.err;
    pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
}
int xmain()
{
    int count=0;
printf("System begin \n");
    PID_init();

    while(count<1000)
    {
        float speed=PID_realize(200.0);
        printf("%f\n",speed);
        count++;
    }
    printf("%llu\n",typeid (count).hash_code());
return 0;}
