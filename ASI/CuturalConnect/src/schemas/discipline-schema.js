const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const disciplineSchema = new Schema({
  nome: String,
  qnt_aulas: Number,
  estudantes: Array
});

const discipline = mongoose.model('disciplines', disciplineSchema);

module.exports = discipline