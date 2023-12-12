const mongoose = require('mongoose');

const Schema = mongoose.Schema;

const studentSchema = new Schema({
  email: String,
  nome: String,
  senha: String,
});

const student = mongoose.model('students', studentSchema);

module.exports = student