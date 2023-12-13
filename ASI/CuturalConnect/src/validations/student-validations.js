const yup = require('yup')

const schemaLogin = yup.object().shape({
  email: yup.string().email('Insira um e-mail válido').required('O e-mail é obrigatório'),
  senha: yup.string().required('A senha é obrigatória'),
})

const schemaRegister = yup.object().shape({
  email: yup.string().email('Insira um e-mail válido').required('O e-mail é obrigatório'),
  nome: yup.string().required('O nome é obrigatório'),
  senha: yup.string().required('A senha é obrigatória'),
  disciplina: yup.string().required('A disciplina é obrigatória'),
})

class studentValidation {
  static login(data) {
    try {
      schemaLogin.validateSync(data)
      return schemaLogin.noUnknown().cast(data)
    } catch (error) {
        throw new Error(error.message, 400)
    }
  }

  static register(data) {
    try {
      schemaRegister.validateSync(data)
      return schemaRegister.noUnknown().cast(data)
    } catch (error) {
        throw new Error(error.message, 400)
    }
  }
}

module.exports = { studentValidation }