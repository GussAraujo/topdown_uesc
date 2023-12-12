const { studentService } = require('../services/student-service')
const { studentValidation } = require('../validations/student-validations')

class studentHandlers {
  /**
   * @required
   * @in req.body
   * @param {import('express').Request} req
   * 
   * @required
   * @in req.body
   * @param {import('express').Response} res
   * 
   * @required
   * @in req.body
   * @param {string} email
   * 
   * @required
   * @in req.body
   * @param {string} senha
   */
  static async login(req, res){
    try {
      const { email, senha } = studentValidation.login(req.body)
      const response = await studentService.login({ email, senha })
      if (response.length > 0)
        res.status(200).send({ message: 'Login feito com sucesso!', data: response._id })
      else
        res.status(404).send({ message: 'Estudante não encontrado!'})
    } catch (error) {
      throw new Error(error.message)
    }
  }

  /**
   * @required
   * @in req.body
   * @param {import('express').Request} req
   * 
   * @required
   * @in req.body
   * @param {import('express').Response} res 
   * 
   * @required
   * @in req.body
   * @param {string} email
   * 
   * @required
   * @in req.body
   * @param {string} nome
   * 
   * @required
   * @in req.body
   * @param {string} senha
   */
  static register(req, res){
    try {
      const { email, nome, senha } = studentValidation.register(req.body)
      studentService.register({ email, nome, senha})
      res.send({ message: 'Estudante criado com sucesso!' })
    } catch (error) {
      throw new Error(error.message)
    }
  }
}

module.exports = { studentHandlers }