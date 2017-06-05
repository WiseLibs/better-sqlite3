// smtc_Output.cpp
//

#include "smtc_Output.h"
// std lib
#include <unistd.h>
#include <cctype>

#include <iostream>

// semantic
#include "smtc_CreateFile.h"
#include "smtc_File.h"

// config
#include "conf_Config.h"

// util
#include "util_FileOp.h"
#define LZZ_INLINE inline
namespace
{
  using namespace smtc;
}
namespace
{
  using namespace util;
}
namespace
{
  void getFullname (String const & path, String const & base, String const & ext, String & fullname, String & name);
}
namespace
{
  String getIncludeGuardName (String const & name, String const & ext);
}
namespace
{
  void printInfo (FilePtr const & file);
}
namespace
{
  void getFullname (String const & path, String const & base, String const & ext, String & fullname, String & name)
  {
    name = file_op::addExt (base, ext);
    fullname = file_op::join (path, name);
  }
}
namespace
{
  String getIncludeGuardName (String const & name, String const & ext)
  {
    String result = "LZZ_";
    String const & package = conf::getOptionValue (conf::opt_package);
    if (! package.empty ())
    {
      result += package;
      result += '_';
    }
    result += name;
    result += '_';
    result += ext;
    // replace non identifier chars with underscore
    for (StringIter i = result.begin (); i != result.end (); ++ i)
    {
      char & ch = * i;
      if (! isalnum (ch))
      {
        ch = '_';
      }
    }
    return result;
  }
}
namespace
{
  void printInfo (FilePtr const & file)
  {
    // info goes in header part of file
    file->header () << "// " << file->getName () << '\n';
    file->header () << "//" << '\n';
    file->header () << '\n';
  }
}
namespace smtc
{
  Output::Output (util::String const & fullname)
    : m_lex_done (false)
    {
      // get path and base name
      file_op::getPathAndName (fullname, m_path, m_base);
      String const & out_path = conf::getOptionValue (conf::opt_out_dir);
      if (out_path.length () > 0)
      {
        m_path = out_path;
      }
      m_base = file_op::remExt (m_base);
    }
}
namespace smtc
{
  Output::~ Output ()
    {}
}
namespace smtc
{
  void Output::close (bool do_write)
    {
      closeInlFile (do_write);
      closeHdrFile (do_write);
      closeSrcFile (do_write);
      closeTplFile (do_write);
      closeTnlFile (do_write);
    }
}
namespace smtc
{
  FilePtr const & Output::getHdrFile ()
    {
      openHdrFile ();
      return m_hdr_file;
    }
}
namespace smtc
{
  FilePtr const & Output::getSrcFile ()
    {
      openSrcFile ();
      return m_src_file;
    }
}
namespace smtc
{
  FilePtr const & Output::getInlFile ()
    {
      openInlFile ();
      return m_inl_file;
    }
}
namespace smtc
{
  FilePtr const & Output::getTplFile ()
    {
      openTplFile ();
      return m_tpl_file;
    }
}
namespace smtc
{
  FilePtr const & Output::getTnlFile ()
    {
      openTnlFile ();
      return m_tnl_file;
    }
}
namespace smtc
{
  bool Output::hasHdrFile (FilePtr & file) const
    {
      bool result = false;
      if (m_hdr_file.isSet ())
      {
        file = m_hdr_file;
        result = true;
      }
      return result;
    }
}
namespace smtc
{
  bool Output::hasSrcFile (FilePtr & file) const
    {
      bool result = false;
      if (m_src_file.isSet ())
      {
        file = m_src_file;
        result = true;
      }
      return result;
    }
}
namespace smtc
{
  bool Output::hasInlFile (FilePtr & file) const
    {
      bool result = false;
      if (m_inl_file.isSet ())
      {
        file = m_inl_file;
        result = true;
      }
      return result;
    }
}
namespace smtc
{
  bool Output::hasTplFile (FilePtr & file) const
    {
      bool result = false;
      if (m_tpl_file.isSet ())
      {
        file = m_tpl_file;
        result = true;
      }
      return result;
    }
}
namespace smtc
{
  bool Output::hasTnlFile (FilePtr & file) const
    {
      bool result = false;
      if (m_tnl_file.isSet ())
      {
        file = m_tnl_file;
        result = true;
      }
      return result;
    }
}
namespace smtc
{
  void Output::lexDone ()
    {
      // print begin code
      if (m_hdr_file.isSet ())
      {
        beginHdrCode ();
      }
      if (m_src_file.isSet ())
      {
        beginSrcCode ();
      }
      if (m_inl_file.isSet ())
      {
        beginInlCode ();
      }
      if (m_tnl_file.isSet ())
      {
        beginTnlCode ();
      }
      m_lex_done = true;
    }
}
namespace smtc
{
  FilePtr Output::createFile (conf::StringOption const & opt_ext, conf::BoolOption const & opt_line, conf::BoolOption const & opt_smart_write)
    {
      String fullname, name;
      String const & ext = conf::getOptionValue (opt_ext);
      getFullname (m_path, m_base, ext, fullname, name);
      return smtc::createFile (fullname, name, ext, conf::getOptionValue (opt_line), conf::getOptionValue (opt_smart_write));
    }
}
namespace smtc
{
  void Output::deleteFile (conf::StringOption const & opt_ext)
    {
      String fullname, name;
      String const & ext = conf::getOptionValue (opt_ext);
      getFullname (m_path, m_base, ext, fullname, name);
      if (file_op::exists (fullname))
      {
        unlink (fullname.c_str ());
      }
    }
}
namespace smtc
{
  void Output::openHdrFile ()
    {
      if (! m_hdr_file.isSet ())
      {
        // create file
        m_hdr_file = createFile (conf::opt_hdr_ext, conf::opt_hdr_line, conf::opt_hdr_smart_write);

        // info
        printInfo (m_hdr_file);

        // include guard
        String guard_name = getIncludeGuardName (m_base, m_hdr_file->getExt ());
        m_hdr_file->header () << "#ifndef " << guard_name << '\n';
        m_hdr_file->header () << "#define " << guard_name << '\n';

        // define inline macro for header inlines 
        m_hdr_file->top () << "#define LZZ_INLINE inline" << '\n';

        // open source too?
        if (conf::getOptionValue (conf::opt_src_if_hdr))
        {
          openSrcFile ();
        }

        // if lexer is done, set inline macro
        if (m_lex_done)
        {
          beginHdrCode ();
        }
      }
    }
}
namespace smtc
{
  void Output::beginHdrCode ()
    {}
}
namespace smtc
{
  void Output::closeHdrFile (bool do_write)
    {
      if (do_write && m_hdr_file.isSet ())
      {
        // undef LZZ_INLINE before rest
        m_hdr_file->body () << "#undef LZZ_INLINE" << '\n';

        // inline file
        if (conf::getOptionValue (conf::opt_inl_inl) && (m_hdr_file->hasSection (INLINE_USER_SECTION) || m_hdr_file->hasSection (INLINE_BODY_SECTION)))
        {
          assert (! m_inl_file.isSet ());
          m_hdr_file->inlineHeader () << "#ifdef LZZ_ENABLE_INLINE" << '\n';
          m_hdr_file->inlineTop () << "#define LZZ_INLINE inline" << '\n';
          m_hdr_file->inlineBody () << "#undef LZZ_INLINE" << '\n';
          m_hdr_file->inlineTail () << "#endif" << '\n';
        }
        else if (m_inl_file.isSet ())
        {
          m_hdr_file->tail () << "#ifdef LZZ_ENABLE_INLINE" << '\n';
          m_hdr_file->tail () << "#include \"" << m_inl_file->getName () << '\"' << '\n';
          m_hdr_file->tail () << "#endif" << '\n';
        }

        // include inline template file if created
        if (m_tnl_file.isSet ())
        {
          if (m_tpl_file.isSet ())
          {
            m_hdr_file->tail () << "#ifdef LZZ_ENABLE_INLINE" << '\n';
          }
          m_hdr_file->tail () << "#include \"" << m_tnl_file->getName () << '\"' << '\n';
          if (m_tpl_file.isSet ())
          {
            m_hdr_file->tail () << "#endif" << '\n';
          }
        }

        // close include guard
        m_hdr_file->tail () << "#endif" << '\n';

        // close file
        m_hdr_file->close (HEADER_FILE);
      }
      else if (conf::getOptionValue (conf::opt_delete_old))
      {
        deleteFile (conf::opt_hdr_ext);
      }
    }
}
namespace smtc
{
  void Output::openSrcFile ()
    {
      if (! m_src_file.isSet ())
      {
        // create file
        m_src_file = createFile (conf::opt_src_ext, conf::opt_src_line, conf::opt_src_smart_write);

        // info
        printInfo (m_src_file);

        // include header file as first line
        openHdrFile ();
        m_src_file->header () << "#include \"" << m_hdr_file->getName () << '\"' << '\n';

        // define inline macro for static and unnamed namespace inlines 
        m_src_file->top () << "#define LZZ_INLINE inline" << '\n';

        // if lexer is done, set inline macro
        if (m_lex_done)
        {
          beginSrcCode ();
        }
      }
    }
}
namespace smtc
{
  void Output::beginSrcCode ()
    {}
}
namespace smtc
{
  void Output::closeSrcFile (bool do_write)
    {
      if (do_write && m_src_file.isSet ())
      {
        // inline file
        if (conf::getOptionValue (conf::opt_inl_inl) && (m_hdr_file->hasSection (INLINE_USER_SECTION) || m_hdr_file->hasSection (INLINE_BODY_SECTION)))
        {
          assert (! m_inl_file.isSet ());
          m_src_file->inlineHeader () << "#ifndef LZZ_ENABLE_INLINE" << '\n';
          m_src_file->inlineTop () << "#define LZZ_INLINE" << '\n';
          m_src_file->inlineBody () << "#undef LZZ_INLINE" << '\n';
          m_src_file->inlineTail () << "#endif" << '\n';
        }
        else if (m_inl_file.isSet ())
        {
          m_src_file->header () << "#ifndef LZZ_ENABLE_INLINE" << '\n';
          m_src_file->header () << "#include \"" << m_inl_file->getName () << '\"' << '\n';
          m_src_file->header () << "#endif" << '\n';
        }

        // remove inline macro
        m_src_file->body () << "#undef LZZ_INLINE" << '\n';
        
        // close file
        m_src_file->close (SOURCE_FILE);
      }
      else if (conf::getOptionValue (conf::opt_delete_old))
      {
        deleteFile (conf::opt_src_ext);
      }
    }
}
namespace smtc
{
  void Output::openInlFile ()
    {
      if (! m_inl_file.isSet ())
      {
        assert (! conf::getOptionValue (conf::opt_inl_inl));

        // create file
        m_inl_file = createFile (conf::opt_inl_ext, conf::opt_inl_line, conf::opt_inl_smart_write);

        printInfo (m_inl_file);

        // must open header and source
        openHdrFile ();
        openSrcFile ();

        // inline macro
        m_inl_file->top () << "#ifdef LZZ_ENABLE_INLINE" << '\n';
        m_inl_file->top () << "#define LZZ_INLINE inline" << '\n';
        m_inl_file->top () << "#else" << '\n';
        m_inl_file->top () << "#define LZZ_INLINE" << '\n';
        m_inl_file->top () << "#endif" << '\n';

        // set inline macro after all include blocks
        if (m_lex_done)
        {
          beginInlCode ();
        }
      }
    }
}
namespace smtc
{
  void Output::beginInlCode ()
    {}
}
namespace smtc
{
  void Output::closeInlFile (bool do_write)
    {
      if (do_write && m_inl_file.isSet ())
      {
        // remove inline macro
        m_inl_file->body () << "#undef LZZ_INLINE" << '\n';
        
        // close file
        m_inl_file->close (INLINE_FILE);
      }
      else if (conf::getOptionValue (conf::opt_delete_old))
      {
        if (! conf::getOptionValue (conf::opt_inl_inl))
        {
          deleteFile (conf::opt_inl_ext);
        }
      }
    }
}
namespace smtc
{
  void Output::openTplFile ()
    {
      if (! m_tpl_file.isSet ())
      {
        // create file
        m_tpl_file = createFile (conf::opt_tpl_ext, conf::opt_tpl_line, conf::opt_tpl_smart_write);

        // info
        printInfo (m_tpl_file);

        // include header file
        openHdrFile ();
        m_tpl_file->header () << "#include \"" << m_hdr_file->getName () << '\"' << '\n';
      }
    }
}
namespace smtc
{
  void Output::closeTplFile (bool do_write)
    {
      if (do_write && m_tpl_file.isSet ())
      {
        // include template inline file if exists
        if (m_tnl_file.isSet ())
        {
          // write to header part of file
          m_tpl_file->header () << "#ifndef LZZ_ENABLE_INLINE" << '\n';
          m_tpl_file->header () << "#include \"" << m_tnl_file->getName () << '\"' << '\n';
          m_tpl_file->header () << "#endif" << '\n';
        }

        // close file
        m_tpl_file->close (TEMPLATE_FILE);
      }
      else if (conf::getOptionValue (conf::opt_delete_old))
      {
        deleteFile (conf::opt_tpl_ext);
      }
    }
}
namespace smtc
{
  void Output::openTnlFile ()
    {
      if (! m_tnl_file.isSet ())
      {
        // create file
        m_tnl_file = createFile (conf::opt_tnl_ext, conf::opt_tnl_line, conf::opt_tnl_smart_write);
        
        // info
        printInfo (m_tnl_file);

        // set inline macro after all include blocks
        m_tnl_file->top () << "#ifdef LZZ_ENABLE_INLINE" << '\n';
        m_tnl_file->top () << "#define LZZ_INLINE inline" << '\n'; 
        m_tnl_file->top () << "#else" << '\n'; 
        m_tnl_file->top () << "#define LZZ_INLINE" << '\n'; 
        m_tnl_file->top () << "#endif" << '\n';

        // requires header and template files
        openHdrFile ();

        // if writing to tnl file and using tpl file, make sure tpl file is open
        if (conf::getOptionValue (conf::opt_tpl))
        {
          openTplFile ();
        }
      }
    }
}
namespace smtc
{
  void Output::beginTnlCode ()
    {}
}
namespace smtc
{
  void Output::closeTnlFile (bool do_write)
    {
      if (do_write && m_tnl_file.isSet ())
      {
        // remove inline macro
        m_tnl_file->body () << "#undef LZZ_INLINE" << '\n';

        // close file
        m_tnl_file->close (TEMPLATE_INLINE_FILE);
      }
      else if (conf::getOptionValue (conf::opt_delete_old))
      {
        deleteFile (conf::opt_tnl_ext);
      }
    }
}
#undef LZZ_INLINE
