const { studentService } = require('../services/student-service')
const { studentValidation } = require('../validations/student-validations')

class handlers {
  /**
   * @path /student
   * @method post
   * @function create
   * 
   * @required
   * @in body
   * @param {string} email
   * 
   * @required
   * @in body
   * @param {string} senha
   */
  static create(event){
    try {
      const { email, senha } = studentValidation.create(event)
      const response = studentService.create({ email, senha })
      return { message: 'Estudante criado com sucesso!', data: response }
    } catch (error) {
      throw new Error(error.message)
    }
  }
}

module.exports = handlers