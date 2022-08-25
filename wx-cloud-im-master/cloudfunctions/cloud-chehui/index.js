// 云函数入口文件
const cloud = require('wx-server-sdk');
cloud.init({
  env: cloud.DYNAMIC_CURRENT_ENV
})
const db = cloud.database();
// 用户信息记录表
const MSG = 'chat-msgs';
// 云函数入口函数
exports.main = async (event, context) => {
  // const wxContext = cloud.getWXContext()
  // console.log(1);
  try {
    
    return await db.collection(MSG)
    .where({
      _id : event.item
    }).remove({
      // success: document.write("已撤回一条消息")
    });
      // .update({
    //   data:{
    //     bool :true
    //   }
    // })
  } 
  catch (e) {
    console.error(e)
  }
  
}