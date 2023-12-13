const discipline = require("../schemas/discipline-schema")

class disciplineService {
  static async addStudent({ idEstudante, disciplina }) {
    try {
      const disciplineFind = await discipline.find({ nome: disciplina }).lean()
      if (disciplineFind.length) {
        const { _id, estudantes } = disciplineFind[0]
        estudantes.push(idEstudante)
        return discipline.updateOne({ _id }, { estudantes })
      }
      throw new Error('Disciplina não encontrada')
    } catch (error) {
      throw new Error(error.message)
    }    
  }
}

module.exports = { disciplineService }