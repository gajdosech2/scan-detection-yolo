/*
  Copyright (C) Skeletex Research, s.r.o. - All Rights Reserved
  Unauthorized copying of this file, via any medium is strictly prohibited
  Proprietary and confidential
*/
#ifndef UTILS_WX_WIDGETS_DIALOG_H
#define UTILS_WX_WIDGETS_DIALOG_H

#include <Utils/DialogInterface.h>

#include <wx/app.h>
#include <wx/msgdlg.h>
#include <wx/wxprec.h>
#include <wx/wfstream.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>

/*
  To make the "stay on top" dialog feature work properly, the "top window" must be set
  Example:
    wxFrame dummy_window;
    dummy_window.SetHWND(hiro::GetWindowHandle());
    dummy_window.Show();
    wxTheApp->SetTopWindow(&dummy_window);
*/

class WxWidgetsDialog : public IDialogInterface
{
public:
  virtual std::optional<std::string> GetPathFromDirectorySelectionDialog(const std::wstring &title, const std::string &default_path = "") const override
  {
    wxDirDialog selectDirDialog(wxTheApp->GetTopWindow(), title, default_path, wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (selectDirDialog.ShowModal() == wxID_CANCEL)
    {
      return std::nullopt;
    }

    return selectDirDialog.GetPath().ToStdString();
  };
  virtual std::vector<std::string> GetPathsFromFileSelectionDialog(const std::wstring &title, const std::string &wildcard, bool enable_multiselect, const std::string &default_path = "") const override
  {
    long dialogFlags = wxFD_OPEN | wxFD_FILE_MUST_EXIST;
    if (enable_multiselect)
    {
      dialogFlags |= wxFD_MULTIPLE;
    }

    std::vector<std::string> returnPaths;

    wxFileDialog openFileDialog(wxTheApp->GetTopWindow(), title, default_path, "", wildcard, dialogFlags);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
    {
      return returnPaths;
    }

    wxArrayString paths;
    openFileDialog.GetPaths(paths);
    for (const auto &path : paths)
    {
      returnPaths.push_back(path.ToStdString());
    }

    return returnPaths;
  };
  virtual std::optional<std::string> GetPathFromFileSaveDialog(const std::wstring &title, const std::string &wildcard, bool overwrite_prompt_enabled, const std::string &default_path = "") const override
  {
    long flags = wxFD_SAVE;
    if (overwrite_prompt_enabled)
    {
      flags |= wxFD_OVERWRITE_PROMPT;
    }
    wxFileDialog saveFileDialog(wxTheApp->GetTopWindow(), title, default_path, "", wildcard, flags);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
      return std::nullopt;
    }

    return saveFileDialog.GetPath().ToStdString();
  };

  virtual void ShowErrorMessage(const std::wstring &message, const std::wstring &title = L"Message") const override
  {
    wxMessageBox(message, title, wxICON_ERROR, wxTheApp->GetTopWindow());
  }

  virtual void ShowWarningMessage(const std::wstring &message, const std::wstring &title = L"Message") const override
  {
    wxMessageBox(message, title, wxICON_WARNING, wxTheApp->GetTopWindow());
  };
  virtual void ShowInfoMessage(const std::wstring &message, const std::wstring &title = L"Message") const override
  {
    wxMessageBox(message, title, wxICON_INFORMATION, wxTheApp->GetTopWindow());
  };
  virtual bool ShowConfirmationDialog(const std::wstring &message, const std::wstring &title = L"Confirmation") const override
  {
    return wxMessageBox(message, title, wxYES_NO | wxICON_EXCLAMATION, wxTheApp->GetTopWindow()) == wxYES;
  };
};

#endif /* !UTILS_WX_WIDGETS_DIALOG_H */