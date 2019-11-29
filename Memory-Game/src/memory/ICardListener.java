/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package memory;

import java.io.IOException;

/**
 *
 * @author zoe
 */
public interface ICardListener {
    void cardClicked(Card theCard) throws IOException;
}
