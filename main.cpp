#include "ncbind/ncbind.hpp"

/**
 * �T���v���l�̎擾
 * ���݂̍Đ��ʒu����w�萔�̃T���v�����擾���Ă��̕��ϒl��Ԃ��܂��B
 * �l�����̃T���v���l�͖�������܂��B
 * @param n �擾����T���v���̐��B�ȗ������ 100
 */
tjs_error
getSample(tTJSVariant *result,tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis)
{
	tjs_error ret = TJS_S_OK;
	tjs_int n = numparams > 0 ? (tjs_int)*param[0] : 100;
	if (n > 0 && result) {
		short *buf = (short*)malloc(n*sizeof(*buf));
		if (buf) {
			tTJSVariant buffer     = (tjs_int)buf;
			tTJSVariant numsamples = n;
			tTJSVariant channel    = 1;
			tTJSVariant *p[3] = {&buffer, &numsamples, &channel};
			if (TJS_SUCCEEDED(ret = objthis->FuncCall(0, L"getVisBuffer", NULL, NULL, 3, p, objthis))) {
				int c=0;
				int sum = 0;
				for (int i=0;i<100;i++) {
					if (buf[i] >= 0) {
						sum += buf[i]; c++;
					}
				}
				*result = c>0 ? sum / c : 0;
			}
			free(buf);
		}
	}
	return ret;
}

NCB_ATTACH_FUNCTION(getSample, WaveSoundBuffer, getSample);
