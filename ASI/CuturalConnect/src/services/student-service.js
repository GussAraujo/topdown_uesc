const student = require("../schemas/student-schema")

class studentService {
  static async login({ email, senha }) {
    try {
      const studentFind = student.find({ email, senha })
      return studentFind
    } catch (error) {
      throw new Error(error.message)
    }    
  }

  static register({ email, nome, senha }) {
    try {
      const newStudent = new student({ email, nome, senha })
      return newStudent.save()
    } catch (error) {
      throw new Error(error.message)
    }    
  }
}

module.exports = { studentService }