# iOSCountDown
iOS开发,实现手机获取验证码倒计时功能

##### 个人链接

* [个人博客](https://nslog-yuhaitao.github.io ) : 个人博客主页
* [iOS频道(iOSPD)](http://www.jianshu.com/collection/d76ac79331c6): 这是我个人整理的一个技术专题, 这里的文章都是比较有技术含量(不断更新)!
* 微信公众号 : 

![微信公众号.jpg](http://upload-images.jianshu.io/upload_images/2248913-22bc242c26133c62.jpg?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

* 详细文章请见简书:[iOS开发中,实现手机获取验证码倒计时功能](http://www.jianshu.com/p/4e3414c60fb1)
* 敬请关注,代码将持续更新...


##### 功能描述
前言 : 一些App注册时可能需要获取手机验证码,这时就会有个倒计时的功能,这个功能会告诉用户正在给他(她)的手机发送验证码,那好今天我就做一下倒计时功能的显示功能,希望能对大家有所帮助!

* 先看一下效果图吧!

![CountDown](http://upload-images.jianshu.io/upload_images/2248913-a1cce5aa8660fefe.gif?imageMogr2/auto-orient/strip)


* 代码部分(按钮点击事件)</br>
  注意:这里必须开启线程!详细细注释请看代码里面.
  
~~~
    //设置倒计时时间
    //通过检验发现，方法调用后，timeout会先自动-1，所以如果从15秒开始倒计时timeout应该写16
    //__block 如果修饰指针时，指针相当于弱引用，指针对指向的对象不产生引用计数的影响
            __block int timeout = 16;
            //获取全局队列
            dispatch_queue_t global = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
            //创建一个定时器，并将定时器的任务交给全局队列执行(并行，不会造成主线程阻塞)
            dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, global);
            // 设置触发的间隔时间
            dispatch_source_set_timer(timer, DISPATCH_TIME_NOW, 1.0 * NSEC_PER_SEC, 0 * NSEC_PER_SEC);
            //1.0 * NSEC_PER_SEC  代表设置定时器触发的时间间隔为1s
            //0 * NSEC_PER_SEC    代表时间允许的误差是 0s
    
            //block内部 如果对当前对象的强引用属性修改 应该使用__weak typeof(self)weakSelf 修饰  避免循环调用
            __weak typeof(self)weakSelf = self;
            //设置定时器的触发事件
            dispatch_source_set_event_handler(timer, ^{
                //倒计时  刷新button上的title ，当倒计时时间为0时，结束倒计时
                //1. 每调用一次 时间-1s
                timeout --;

                //2.对timeout进行判断时间是停止倒计时，还是修改button的title
                if (timeout <= 0) {
                    //停止倒计时，button打开交互，背景颜色还原，title还原
                    //关闭定时器
                    dispatch_source_cancel(timer);
                    //MRC下需要释放，这里不需要
                    // dispatch_realse(timer);
                    //button上的相关设置
                    //注意: button是属于UI，在iOS中多线程处理时，UI控件的操作必须是交给主线程(主队列)
                    //在主线程中对button进行修改操作
                    dispatch_async(dispatch_get_main_queue(), ^{
                        weakSelf.downBtn.userInteractionEnabled = YES;//开启交互性
                        weakSelf.downBtn.backgroundColor = [UIColor yellowColor];
                        [weakSelf.downBtn setTitle:@"获取验证码" forState:UIControlStateNormal];
                        });
                }else {
                    //处于正在倒计时，在主线程中刷新button上的title，时间-1秒
                    dispatch_async(dispatch_get_main_queue(), ^{
                        NSString * title = [NSString stringWithFormat:@"%d秒后重新获取验证码",timeout];
                        [weakSelf.downBtn setTitle:title forState:UIControlStateNormal];
                        weakSelf.downBtn.userInteractionEnabled = NO;//关闭交互性
                        });
                }
                });
            dispatch_resume(timer);
~~~

#####  时间: 2016.12.5 11:05 am

##### 声明

* 所有文章出自 [Kenny Hito 的博客](https://nslog-yuhaitao.github.io ) !
* 未经本人允许不得转载, 转载请标明来源与作者, 谢谢合作! 