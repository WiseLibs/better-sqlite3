// smtc_Output.h
//

#ifndef LZZ_smtc_Output_h
#define LZZ_smtc_Output_h
// semantic
#include "smtc_FilePtr.h"

// util
#include "util_String.h"
#define LZZ_INLINE inline
namespace conf
{
  class StringOption;
}
namespace conf
{
  class BoolOption;
}
namespace smtc
{
  class Output
  {
    util::String m_path;
    util::String m_base;
    FilePtr m_hdr_file;
    FilePtr m_src_file;
    FilePtr m_inl_file;
    FilePtr m_tpl_file;
    FilePtr m_tnl_file;
    bool m_lex_done;
  public:
    Output (util::String const & fullname);
    ~ Output ();
    void close (bool do_write);
    FilePtr const & getHdrFile ();
    FilePtr const & getSrcFile ();
    FilePtr const & getInlFile ();
    FilePtr const & getTplFile ();
    FilePtr const & getTnlFile ();
    bool hasHdrFile (FilePtr & file) const;
    bool hasSrcFile (FilePtr & file) const;
    bool hasInlFile (FilePtr & file) const;
    bool hasTplFile (FilePtr & file) const;
    bool hasTnlFile (FilePtr & file) const;
    void lexDone ();
  private:
    FilePtr createFile (conf::StringOption const & opt_ext, conf::BoolOption const & opt_line, conf::BoolOption const & opt_smart_write);
    void deleteFile (conf::StringOption const & opt_ext);
    void openHdrFile ();
    void beginHdrCode ();
    void closeHdrFile (bool do_write);
    void openSrcFile ();
    void beginSrcCode ();
    void closeSrcFile (bool do_write);
    void openInlFile ();
    void beginInlCode ();
    void closeInlFile (bool do_write);
    void openTplFile ();
    void closeTplFile (bool do_write);
    void openTnlFile ();
    void beginTnlCode ();
    void closeTnlFile (bool do_write);
  };
}
#undef LZZ_INLINE
#endif
