#include "stdinc.h"
#include "byte_pattern.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
		byte_pattern::start_log(L"eu4jps");

		// version�𕶎��񂩂�擾
		EU4Version version = Misc::getVersion();
		
		errno_t success = NOERROR;

		// �t�H���g�֘A�̏C��
		success |= Font::init(version);

		// �{���e�L�X�g�\���̏C��
		success |= TextView::init(version);

		// �}�b�v�����ʒu����
		success |= MapAdj::init(version);

		// �}�b�v����justify
		success |= MapJustify::init(version);

		// �}�b�v�����\��
		success |= MapView::init(version);

		// ���̑�
		success |= Misc::init(version);

		//���͏C��
		success |= Input::init(version);

		//IME�C��
		success |= IME::init(version);

		//�c�[���`�b�v�ƃ{�^��
		success |= ButtonAndToolTip::init(version);

		//�c�[���`�b�v�ǉ�����
		success |= ToolTipApx::init(version);

		//�}�b�v��̃|�b�v�A�b�v����
		success |= PopupCharOnMap::init(version);

		// issue19�̏C��
		success |= InputIssue19::init(version);

		// �C�x���g�_�C�A���O�̏C���ƃ}�b�v��̏C��
		success |= EventDialog::init(version);

		// �t�@�C���Z�[�u�֘A
		success |= FileSave::init(version);

		// issue66�̏C��
		success |= Issue66::init(version);

		if (success == NOERROR) {
			//MessageBoxW(NULL, L"[OK]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[NG]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [NG]");
			exit(-1);
		}
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
