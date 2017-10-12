package com.fulong.lyvc.passport;

import com.fulong.lyvc.user.*;

/**
 * 
 * PassportUser
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-11
 */
public class PassportUser implements com.fulong.lyvc.User {

    private com.fulong.longcon.security.User user;
    public PassportUser(com.fulong.longcon.security.User user) {
        this.user = user;
    }

    public long getId() {
        return Long.parseLong(user.getId());
    }

    public String getEmail() {
        return user.getEmail();
    }

    public String getAccountName() {
        return user.getUsername();
    }

    public String getFirstName() {
        return user.getCommonname();
    }

    public String getLastName() {
        return "";
    }

    public String getPassword() {
        throw new UserLibraryException("method is not implemented. ");
    }
}

