# Curriculum-design
- 基于QT做的进制转换，当年就这么混过去了，菜鸟级别的
- wx-cloud-im-master
  - 微信小程序——聊天室
  - 实现情况
    - 三个聊天室
    - 消息撤回（从云数据库删除记录），但是不会显示消息已删除
  - 参考仓库：https://gitee.com/Kindear/wx-cloud-im
## 密码学
- RSA算法
  - [x] 素性检测 Miller-Rabin算法
  - [ ] 大数乘法（中国剩余定理）还未实现。。。n=p×q
  - [x] 扩展欧几里得算法exEuclid——求乘法逆元
  - [x] 大数幂模算法(a^b mod n)
- AES128算法
  - 从文本中读取内容，但是长度还只能≤16字节
