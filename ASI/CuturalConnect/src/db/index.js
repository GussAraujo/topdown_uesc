const mongoose = require('mongoose')

class mongodb {
  static connect() {
    mongoose.connect('mongodb+srv://gusaraujo2504:myR10j8pkr1jRWbr@cluster0.e1zynre.mongodb.net/cutural-connect')
    const db = mongoose.connection;
    db.on('error', console.error.bind(console, 'Erro de conexão ao MongoDB:'));
    db.once('open', () => {
      console.log('Conectado ao MongoDB!');
    })
  }
}


module.exports = { mongodb }