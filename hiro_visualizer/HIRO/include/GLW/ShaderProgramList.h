/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef GLW_SHADER_PROGRAM_LIST_H
#define GLW_SHADER_PROGRAM_LIST_H
#include <Utils/Property.h>
#include <GLW/ShaderProgram.h>



namespace glw
{

  struct GLW_API ShaderPipeline
  {
    ShaderPipeline() : vert(this), tesc(this), tese(this), geom(this), frag(this) {}

    ShaderPipeline(const std::string &base_filename);

    std::map<glw::ShaderType, std::string> GetAll() const { return data_; };

    std::string Get(glw::ShaderType type) { return data_[type]; };

    std::string GetVert() const { return data_.at(glw::ShaderType::vertex); };
    std::string GetTesc() const { return data_.at(glw::ShaderType::tess_ctrl); };
    std::string GetTese() const { return data_.at(glw::ShaderType::tess_eval); };
    std::string GetGeom() const { return data_.at(glw::ShaderType::geometry); };
    std::string GetFrag() const { return data_.at(glw::ShaderType::fragment); };
    void SetVert(const std::string &value) { data_[glw::ShaderType::vertex] = value; };
    void SetTesc(const std::string &value) { data_[glw::ShaderType::tess_ctrl] = value; };
    void SetTese(const std::string &value) { data_[glw::ShaderType::tess_eval] = value; };
    void SetGeom(const std::string &value) { data_[glw::ShaderType::geometry] = value; };
    void SetFrag(const std::string &value) { data_[glw::ShaderType::fragment] = value; };

    utils::Property<ShaderPipeline, std::string, &ShaderPipeline::GetVert, &ShaderPipeline::SetVert> vert;
    utils::Property<ShaderPipeline, std::string, &ShaderPipeline::GetTesc, &ShaderPipeline::SetTesc> tesc;
    utils::Property<ShaderPipeline, std::string, &ShaderPipeline::GetTese, &ShaderPipeline::SetTese> tese;
    utils::Property<ShaderPipeline, std::string, &ShaderPipeline::GetGeom, &ShaderPipeline::SetGeom> geom;
    utils::Property<ShaderPipeline, std::string, &ShaderPipeline::GetFrag, &ShaderPipeline::SetFrag> frag;

  private:
    std::map<glw::ShaderType, std::string> data_
    {
      { glw::ShaderType::vertex, "" },
      { glw::ShaderType::tess_ctrl, "" },
      { glw::ShaderType::tess_eval, "" },
      { glw::ShaderType::geometry, "" },
      { glw::ShaderType::fragment, "" }
    };
  };

  using PProgramList = std::shared_ptr<class ProgramList>;

  class GLW_API ProgramList
  {
  public:

    static PProgramList Create();

  public:

    explicit ProgramList();

    ~ProgramList();

    void ClearAll();

    void Reload();

    void AddFromFile(const std::string &program_name, const ShaderPipeline &files, const std::map<std::string, std::string> replace_map = std::map<std::string, std::string>());

    void AddFromSource(const std::string &program_name, const ShaderPipeline &sources, const std::map<std::string, std::string> replace_map = std::map<std::string, std::string>());

    bool Exist(const std::string &program_name);

    void Use(const std::string &program_name) const;

    std::vector<std::string> GetAllProgramNames() const;

    glw::PProgram GetProgram(const std::string &program_name);

    bool IsEmpty();

  private:
    std::map<std::string, glw::PProgram> programs_;
    std::map<std::string, ShaderPipeline> shader_files_;

    bool LinkAndShowMessages(const glw::PProgram &program_ptr, const std::string &program_name);
    glw::PProgram CreateProgram(const std::string &id);
  };

}
#endif /* !GLW_SHADER_PROGRAM_LIST_H */