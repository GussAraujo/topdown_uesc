const student = require("../schemas/student-schema")
const { disciplineService } = require("./discipline-service")

class studentService {
  static async login({ email, senha }) {
    try {
      const studentFind = await student.find({ email, senha }).lean()
      return studentFind
    } catch (error) {
      throw new Error(error.message)
    }    
  }

  static async register({ email, nome, senha, disciplina }) {
    try {
      const newStudent = new student({ email, nome, senha, disciplina })
      if (newStudent.save()) {
        await disciplineService.addStudent({ idEstudante: newStudent._id, disciplina })
      }
    } catch (error) {
      throw new Error(error.message)
    }    
  }
}

module.exports = { studentService }