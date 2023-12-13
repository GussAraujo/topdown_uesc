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
        res.status(200).send({ message: 'Login feito com sucesso!', nome: response[0].nome })
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
   * 
   * @required
   * @in req.body
   * @param {string} disciplina
   */
  static async register(req, res){
    try {
      const { email, nome, senha, disciplina } = studentValidation.register(req.body)
      await studentService.register({ email, nome, senha, disciplina })
      res.send({ message: 'Estudante criado com sucesso!' })
    } catch (error) {
      throw new Error(error.message)
    }
  }
}

module.exports = { studentHandlers }